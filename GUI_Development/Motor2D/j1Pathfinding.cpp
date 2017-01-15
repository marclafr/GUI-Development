#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1PathFinding.h"
#include"j1Render.h"
#include"j1Scene.h"

j1PathFinding::j1PathFinding() : j1Module(), map(NULL), last_path(DEFAULT_PATH_LENGTH), width(0), height(0)
{
	name.create("pathfinding");
}

// Destructor
j1PathFinding::~j1PathFinding()
{
	RELEASE_ARRAY(map);
}

// Called before quitting
bool j1PathFinding::CleanUp()
{
	LOG("Freeing pathfinding library");

	last_path.Clear();
	RELEASE_ARRAY(map);
	return true;
}

// Sets up the walkability map
void j1PathFinding::SetMap(uint width, uint height, uchar* data)
{
	this->width = width;
	this->height = height;
	RELEASE_ARRAY(map);
	map = new uchar[width*height];
	memcpy(map, data, width*height);
}

// Utility: return true if pos is inside the map boundaries
bool j1PathFinding::CheckBoundaries(const iPoint& pos) const
{
	return (pos.x >= 0 && pos.x <= (int)width &&
		pos.y >= 0 && pos.y <= (int)height);
}

// Utility: returns true is the tile is walkable
bool j1PathFinding::IsWalkable(const iPoint& pos) const
{
	uchar t = GetTileAt(pos);
	return t != INVALID_WALK_CODE && t > 0;
}

// Utility: return the walkability value of a tile
uchar j1PathFinding::GetTileAt(const iPoint& pos) const
{
	if (CheckBoundaries(pos))
		return map[(pos.y*width) + pos.x];

	return INVALID_WALK_CODE;
}

// To request all tiles involved in the last generated path
const p2DynArray<iPoint>* j1PathFinding::GetLastPath() const
{
	return &last_path;
}

// PathList ------------------------------------------------------------------------
// Looks for a node in this list and returns it's list node or NULL
// ---------------------------------------------------------------------------------
p2List_item<PathNode>* PathList::Find(const iPoint& point) const
{
	p2List_item<PathNode>* item = list.start;
	while (item)
	{
		if (item->data.pos == point)
			return item;
		item = item->next;
	}
	return NULL;
}

// PathList ------------------------------------------------------------------------
// Returns the Pathnode with lowest score in this list or NULL if empty
// ---------------------------------------------------------------------------------
p2List_item<PathNode>* PathList::GetNodeLowestScore() const
{
	p2List_item<PathNode>* ret = NULL;
	int min = 65535;

	p2List_item<PathNode>* item = list.end;
	while (item)
	{
		if (item->data.Score() < min)
		{
			min = item->data.Score();
			ret = item;
		}
		item = item->prev;
	}
	return ret;
}

// PathNode -------------------------------------------------------------------------
// Convenient constructors
// ----------------------------------------------------------------------------------
PathNode::PathNode() : g(-1), h(-1), pos(-1, -1), parent(NULL)
{}

PathNode::PathNode(int g, int h, const iPoint& pos, const PathNode* parent) : g(g), h(h), pos(pos), parent(parent)
{}

PathNode::PathNode(const PathNode& node) : g(node.g), h(node.h), pos(node.pos), parent(node.parent)
{}

// PathNode -------------------------------------------------------------------------
// Fills a list (PathList) of all valid adjacent pathnodes
// ----------------------------------------------------------------------------------
uint PathNode::FindWalkableAdjacents(PathList& list_to_fill) const
{
	iPoint cell;
	uint before = list_to_fill.list.count();

	// north
	cell.create(pos.x, pos.y + 1);
	if (App->pathfinding->IsWalkable(cell))
		list_to_fill.list.add(PathNode(-1, -1, cell, this));

	// south
	cell.create(pos.x, pos.y - 1);
	if (App->pathfinding->IsWalkable(cell))
		list_to_fill.list.add(PathNode(-1, -1, cell, this));

	// east
	cell.create(pos.x + 1, pos.y);
	if (App->pathfinding->IsWalkable(cell))
		list_to_fill.list.add(PathNode(-1, -1, cell, this));

	// west
	cell.create(pos.x - 1, pos.y);
	if (App->pathfinding->IsWalkable(cell))
		list_to_fill.list.add(PathNode(-1, -1, cell, this));

	//Northwest
	cell.create(pos.x - 1, pos.y + 1);
	if (App->pathfinding->IsWalkable(cell))
		list_to_fill.list.add(PathNode(-1, -1, cell, this));

	//Northeast
	cell.create(pos.x + 1, pos.y + 1);
	if (App->pathfinding->IsWalkable(cell))
		list_to_fill.list.add(PathNode(-1, -1, cell, this));

	//Southwest
	cell.create(pos.x - 1, pos.y - 1);
	if (App->pathfinding->IsWalkable(cell))
		list_to_fill.list.add(PathNode(-1, -1, cell, this));

	//Southeast
	cell.create(pos.x + 1, pos.y - 1);
	if (App->pathfinding->IsWalkable(cell))
		list_to_fill.list.add(PathNode(-1, -1, cell, this));

	return list_to_fill.list.count();
}

// PathNode -------------------------------------------------------------------------
// Calculates this tile score
// ----------------------------------------------------------------------------------
int PathNode::Score() const
{
	return g + h;
}

// PathNode -------------------------------------------------------------------------
// Calculate the F for a specific destination tile
// ----------------------------------------------------------------------------------
int PathNode::CalculateF(const iPoint& destination)
{
	g = parent->g + 1;
	h = pos.DistanceManhattan(destination);

	return g + h;
}

// ----------------------------------------------------------------------------------
// Actual A* algorithm: return number of steps in the creation of the path or -1 ----
// ----------------------------------------------------------------------------------
int j1PathFinding::CreatePath(const iPoint& origin, const iPoint& destination)
{
	if (IsWalkable(origin) == false || IsWalkable(destination) == false) 
	{
		return -1;
	}
	CreateTeleports();
	PathList open;
	PathNode originNode;
	originNode.pos.x = origin.x;
	originNode.pos.y = origin.y;
	open.list.add(originNode);
	PathList close;
	while (open.list.count() != 0) 
	{
		p2List_item<PathNode>*activeNode;
		activeNode = close.list.add(open.GetNodeLowestScore()->data);
		open.list.del(open.GetNodeLowestScore());
		p2List_item<Teleport> *templisttp;
		for (templisttp = Myteleport.start; templisttp != nullptr; templisttp = templisttp->next)
		{
			if (activeNode->data.pos == templisttp->data.origin.pos) 
			{
				activeNode = Newnodeteleport(activeNode, close);
				break;//only can enter in one portal
			}
		}
		//for (int i = 0; i < last_path.Count(); i++) {
		SDL_Rect r;
		r.w = 64;
		r.h = 33;
		r.x = 0;
		r.y = 15;
		//App->render->Blit(App->scene->movingtile, last_path[i].x, last_path[i].y, &r);
		App->render->Blit(App->scene->movingtile, activeNode->data.pos.x, activeNode->data.pos.y, &r);
		//}

		if (close.list.end->data.pos == destination)
		{
			last_path.Clear();
			PathNode item = activeNode->data;
			while (item.parent != nullptr) 
			{
				last_path.PushBack(item.pos);
				item = *item.parent;
			}
			last_path.PushBack(origin);
			last_path.Flip();
			return last_path.Count();
		}
		PathList pathtemp;
		activeNode->data.FindWalkableAdjacents(pathtemp);
		for (p2List_item<PathNode> *neitemp = pathtemp.list.start; neitemp != nullptr; neitemp = neitemp->next) 
		{
			if (close.Find(neitemp->data.pos) == NULL) 
			{
				p2List_item<Teleport> *temptelep;
				WorthTeleport(neitemp, destination);
				if (p2List_item<PathNode> *otherneitemp = open.Find(neitemp->data.pos)) 
				{
					if (neitemp->data.g < otherneitemp->data.g)
					{
						otherneitemp->data.parent = neitemp->data.parent;
					}
				}
				else {
					open.list.add(neitemp->data);
				}
			}
		}
	}

	return 1;
}


p2List_item<PathNode>* j1PathFinding::Newnodeteleport(p2List_item<PathNode>* activenode, PathList &listclose)
{
	p2List_item<Teleport> *temptelep;
	for (temptelep = Myteleport.start; temptelep != nullptr; temptelep = temptelep->next) 
	{
		if (listclose.list.end->data.pos == temptelep->data.origin.pos)
		{
			temptelep->data.dest.g = activenode->data.g;
			temptelep->data.dest.h = activenode->data.h;
			temptelep->data.dest.parent = &activenode->data;
			return listclose.list.add(temptelep->data.dest);
		}
	}
	return nullptr;
}

bool j1PathFinding::WorthTeleport(p2List_item<PathNode> *Adjacent, iPoint dest)
{
	p2List_item<Teleport> *temptelep;
	for (temptelep = Myteleport.start; temptelep != nullptr; temptelep = temptelep->next)
	{
		if (Adjacent->data.pos.DistanceManhattan(dest) > Adjacent->data.pos.DistanceManhattan(temptelep->data.origin.pos) + temptelep->data.dest.pos.DistanceManhattan(dest)) 
		{
			Adjacent->data.CalculateF(temptelep->data.origin.pos);
			return true;
		}
	}
	Adjacent->data.CalculateF(dest);
	return false;
}

void j1PathFinding::CreateTeleports() 
{
	Teleport TelepA;
	TelepA.origin.pos = iPoint(18, 14);
	TelepA.dest.pos = iPoint(8, 9);
	Myteleport.add(TelepA);
	Teleport TelepB;
	TelepB.origin.pos = iPoint(8, 9);
	TelepB.dest.pos = iPoint(18, 14);
	Myteleport.add(TelepB);
}