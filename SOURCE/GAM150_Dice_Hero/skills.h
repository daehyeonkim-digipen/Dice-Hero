/*
File name: skills.h
Project name: Dice Hero
Author(s): Major - Daehyeon Kim, minor - Taeju Kwon
All content © 2021 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#include "skill.h"

#include <vector>


class SkillTree 
{
public:
    SkillTree(Skill* skill1, Skill* skill2, Skill* skill3, Skill* skill4)
    {
        skills.push_back(skill1);
        skills.push_back(skill2);
        skills.push_back(skill3);
        skills.push_back(skill4);
    }
    SkillTree(Skill* skill1, Skill* skill2, Skill* skill3, Skill* skill4, Skill* skill5)
    {
        skills.push_back(skill1);
        skills.push_back(skill2);
        skills.push_back(skill3);
        skills.push_back(skill4);
        skills.push_back(skill5);
    }
    SkillTree(Skill* skill1, Skill* skill2, Skill* skill3, Skill* skill4, Skill* skill5, Skill* skill6)
    {
        skills.push_back(skill1);
        skills.push_back(skill2);
        skills.push_back(skill3);
        skills.push_back(skill4);
        skills.push_back(skill5);
        skills.push_back(skill6);
    }
    std::vector<Skill*> skills{};
};

inline SkillTree WarriorTree(&warriorSkill1, &warriorSkill2, &warriorSkill3, &warriorSkill4, &warriorSkill5);
inline SkillTree MageTree(&mageSkill1, &mageSkill2, &mageSkill3, &mageSkill4);
inline SkillTree ThiefTree(&thiefSkill1, &thiefSkill2, &thiefSkill3, &thiefSkill4, &thiefSkill5);
inline SkillTree ArcherTree(&archerSkill1, &archerSkill2, &archerSkill3, &archerSkill4, &archerSkill5, &archerSkill6);