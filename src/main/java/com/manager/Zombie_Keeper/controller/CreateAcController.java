package com.manager.Zombie_Keeper.controller;

import java.util.Optional;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import com.manager.Zombie_Keeper.dtos.CreateAcRequest;
import com.manager.Zombie_Keeper.model.Role;
import com.manager.Zombie_Keeper.model.User;
import com.manager.Zombie_Keeper.repository.RoleRepository;
import com.manager.Zombie_Keeper.repository.UserRepository;

import jakarta.validation.Valid;

@RestController()
@RequestMapping("/auth")
public class CreateAcController {
   
    @Autowired
    private UserRepository userRepository;
    @Autowired
    private PasswordEncoder encoder;
    @Autowired
    private RoleRepository roleRepository;

    public CreateAcController(UserRepository userRepository, PasswordEncoder encoder, RoleRepository roleRepository){
        this.userRepository = userRepository;
        this.encoder = encoder;
        this.roleRepository = roleRepository;
    }

    @PostMapping("/register")
    public ResponseEntity<String> createAccount(@RequestBody @Valid CreateAcRequest dto){
        String passEncod = encoder.encode(dto.getPassword());
        
        User  userRegister = new User();

        Role role = roleRepository.findByType(dto.getRole());
        
        if(role != null){
            userRegister.setName(dto.getName());
            userRegister.setUsername(dto.getUsername());
            userRegister.setPassword(passEncod);
            userRegister.setRole(role);
            
            userRepository.save(userRegister);
        
            return ResponseEntity.status(HttpStatus.CREATED).body(" User created");
        }         
        
              
        return ResponseEntity.status(401).body("User not created");

    }



}
