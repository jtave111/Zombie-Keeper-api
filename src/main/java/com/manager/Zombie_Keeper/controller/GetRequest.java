package com.manager.Zombie_Keeper.controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;


@Controller
public class GetRequest {
    
    @GetMapping("/")
    public String getHome(){
        return "home";
    }
    
    @GetMapping("/agents")
    public String getAgents(){

        return "agents";
    }

    @GetMapping("/login")
    public String getLogin(){
        
        return "login";
    }



}
