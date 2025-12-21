package com.manager.Zombie_Keeper.controller;

import java.nio.file.AccessDeniedException;

import org.springframework.http.HttpStatus;
import org.springframework.security.core.Authentication;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;

import com.manager.Zombie_Keeper.dtos.CreateAcRequest;
import com.manager.Zombie_Keeper.model.CustomUserDetails;
import com.manager.Zombie_Keeper.model.User;


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

    @GetMapping("/register")
    public String getRegister() throws AccessDeniedException {
        
       
    
        Authentication auth = SecurityContextHolder.getContext().getAuthentication();

        User user = (User) auth.getPrincipal();

        System.out.println("Usuario logado," + user.getName() + "role " + user.getRole().getType());


        if(!"ADMIN".equals(user.getRole().getType())){


            throw new AccessDeniedException(HttpStatus.UNAUTHORIZED.name());
        }
        
        return "register";
    }
    
}


