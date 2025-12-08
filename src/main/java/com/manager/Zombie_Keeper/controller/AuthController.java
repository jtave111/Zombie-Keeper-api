package com.manager.Zombie_Keeper.controller;

import java.util.Optional;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import com.manager.Zombie_Keeper.dtos.LoginRequest;
import com.manager.Zombie_Keeper.model.User;
import com.manager.Zombie_Keeper.repository.UserRepository;

import jakarta.validation.Valid;

@RestController
@RequestMapping("/auth")
public class AuthController {

    @Autowired
    private UserRepository userRepository;
    @Autowired
    private PasswordEncoder encoder;

    @PostMapping("/login")
    public ResponseEntity<String> login(@RequestBody @Valid LoginRequest loginRequest){
       
       Optional<User> userOptional = userRepository.findByUsername(loginRequest.getUsername());
       

        if(userOptional.isPresent()){

            User user = userOptional.get();

            if(encoder.matches(loginRequest.getPassword(), user.getPassword())){
                return ResponseEntity.ok("Authorized");
            }

        }

       
        return ResponseEntity.status(401).body("User or Password invalid");        
    } 


}
