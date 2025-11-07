#include "collision_manager.h"
#include "scene/components.h"
#include <cmath>
#include <tuple>

struct Collision
{
    CoTransform& trA;
    CoTransform& trB; 
    CoCollider& colA;
    CoCollider& colB;
};
static std::vector<Collision> collisions;

void CollisionManager::Update()
{
    collisions.clear();
    auto group = m_Scene->Group<CoTransform, CoCollider>();
    
    for (auto itA = group.begin(); itA != group.end(); ++itA) {
    auto [trA, colA] = group.get<CoTransform, CoCollider>(*itA);

        for (auto itB = std::next(itA); itB != group.end(); ++itB) {
            auto [trB, colB] = group.get<CoTransform, CoCollider>(*itB);

            if(CheckAABB(trA.transform, trB.transform, colA.size, colB.size)) {
                collisions.push_back({trA, trB, colA, colB});
            }
        }
    }
    
    for(auto& col : collisions)
    {
        ResolveAABB(col.trA.transform, col.trB.transform, col.colA.size, col.colB.size);
    }
}

bool CollisionManager::CheckAABB(glm::mat4& a_pos, glm::mat4& b_pos,
                                 glm::ivec2& a_size, glm::ivec2& b_size)
{
    // Extract translation parts of matrix
    glm::vec2 aWorld = glm::vec2(a_pos[3]); // (x, y)
    glm::vec2 bWorld = glm::vec2(b_pos[3]);

    // Half extents
    glm::vec2 aHalf = glm::vec2(a_size) * 0.5f;
    glm::vec2 bHalf = glm::vec2(b_size) * 0.5f;

    // AABB collision check
    bool overlapX = std::abs(aWorld.x - bWorld.x) < (aHalf.x + bHalf.x);
    bool overlapY = std::abs(aWorld.y - bWorld.y) < (aHalf.y + bHalf.y);

    return overlapX && overlapY;
}

void CollisionManager::ResolveAABB(glm::mat4& a_pos, glm::mat4& b_pos,
                                   glm::ivec2& a_size, glm::ivec2& b_size)
{
    glm::vec2 aWorld = glm::vec2(a_pos[3]); 
    glm::vec2 bWorld = glm::vec2(b_pos[3]);

    glm::vec2 aHalf = glm::vec2(a_size) * 0.5f;
    glm::vec2 bHalf = glm::vec2(b_size) * 0.5f;

    // Calculate overlaps
    float dx = aWorld.x - bWorld.x;
    float px = (aHalf.x + bHalf.x) - std::abs(dx);

    float dy = aWorld.y - bWorld.y;
    float py = (aHalf.y + bHalf.y) - std::abs(dy);

    if (px <= 0 || py <= 0)
        return; // No collision → nothing to resolve

    // Push out along the least penetration axis
    if (px < py) {
        aWorld.x += (dx > 0 ? px : -px);
    } else {
        aWorld.y += (dy > 0 ? py : -py);
    }

    // Write corrected position back to matrix
    a_pos[3].x = aWorld.x;
    a_pos[3].y = aWorld.y;
}

