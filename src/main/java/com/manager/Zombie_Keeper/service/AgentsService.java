package com.manager.Zombie_Keeper.service;

import org.apache.commons.text.similarity.LevenshteinDetailedDistance;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import com.manager.Zombie_Keeper.controller.AgentController;
import com.manager.Zombie_Keeper.model.Agent;
import com.manager.Zombie_Keeper.model.enums.Flags;
import com.manager.Zombie_Keeper.model.enums.Tags;
import com.manager.Zombie_Keeper.repository.AgentRepository;

@Service
public class AgentsService {
    @Autowired
    private AgentController agentController;
    @Autowired
    private AgentRepository agentRepository;
    @Autowired
    private LevenshteinDetailedDistance lvDistace;

    public void updateAgentClassification(Agent agent ){
        Flags flags;
        Tags tags;
            

        String os = agent.getOs();

        


    }


    public String substractOs(String os){


        return "";
    }

}
