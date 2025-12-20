package com.manager.Zombie_Keeper.controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.security.access.AccessDeniedException;
import org.springframework.security.access.prepost.PreAuthorize;
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
import com.manager.Zombie_Keeper.service.AuthService;

import jakarta.validation.Valid;

@RestController
@RequestMapping
public class ApiRegister {

    @Autowired
    private UserRepository userRepository;
    @Autowired
    private PasswordEncoder encoder;
    @Autowired
    private RoleRepository roleRepository;
    @Autowired
    public ApiRegister(UserRepository userRepository, PasswordEncoder encoder, RoleRepository roleRepository){
        this.userRepository = userRepository;
        this.encoder = encoder;
        this.roleRepository = roleRepository;
        
    }
    @Autowired
    AuthService authService;

    @PostMapping("/apir")
    
    public ResponseEntity<String> createAc(
        @RequestBody @Valid CreateAcRequest dto
    ){
        User user = authService.getAuthUser();
      
         System.out.println("Requisição chegou");
            System.out.println("User: " + user.getName());
            System.out.println("Role obj: " + user.getRole());

      

        System.out.println("User: " + user.getName() + " role: " + user.getRole().getType());
                
    
        if(!dto.getPassword().equals(dto.getRepeetPassword())) return ResponseEntity.status(400).body("Passwords do not know");

        String passEncod = encoder.encode(dto.getPassword());
        User  userRegister = new User();
        Role role = roleRepository.findByType(dto.getRole());
        
        if(role != null){
            userRegister.setName(dto.getName());
            userRegister.setUsername(dto.getUsername());
            userRegister.setPassword(passEncod);
            userRegister.setRole(role);
            
            userRepository.save(userRegister);
            
            System.out.println("Requisição chegou ao final ");
            return ResponseEntity.status(HttpStatus.CREATED).body(" User created");
        }         
        
              
        return ResponseEntity.status(401).body("User not created");
    }
    
}
