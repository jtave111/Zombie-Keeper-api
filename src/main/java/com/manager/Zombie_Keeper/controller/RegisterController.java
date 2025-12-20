package com.manager.Zombie_Keeper.controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;

import com.manager.Zombie_Keeper.dtos.CreateAcRequest;
import com.manager.Zombie_Keeper.model.User;
import com.manager.Zombie_Keeper.repository.UserRepository;

@Controller
@RequestMapping("/register")
public class RegisterController {

 
    @GetMapping
    public String getRegister() {
        
        return "register";
    }


}
