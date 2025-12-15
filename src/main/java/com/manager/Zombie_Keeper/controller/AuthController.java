package com.manager.Zombie_Keeper.controller;

import java.util.Collection;
import java.util.Optional;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.security.authentication.UsernamePasswordAuthenticationToken;
import org.springframework.security.core.Authentication;
import org.springframework.security.core.GrantedAuthority;
import org.springframework.security.core.context.SecurityContext;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.security.web.context.HttpSessionSecurityContextRepository;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import com.manager.Zombie_Keeper.dtos.LoginRequest;
import com.manager.Zombie_Keeper.model.User;
import com.manager.Zombie_Keeper.repository.UserRepository;

import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpSession;
import jakarta.validation.Valid;

@RestController
@RequestMapping("/auth")
public class AuthController {

    @Autowired
    private UserRepository userRepository;
    @Autowired
    private PasswordEncoder encoder;

    @PostMapping("/login")
    public ResponseEntity<String> login(@RequestBody @Valid LoginRequest loginRequest, HttpServletRequest request){
       
       Optional<User> userOptional = userRepository.findByUsername(loginRequest.getUsername());
       
       System.out.println(">>> Requeste for user: " + loginRequest.getUsername());

        if(userOptional.isPresent()){

            User user = userOptional.get();

            if(encoder.matches(loginRequest.getPassword(), user.getPassword())){
                UserDetails userDetails = user;
                Collection<? extends GrantedAuthority> authorities = userDetails.getAuthorities();
                

                Authentication  authentication = new UsernamePasswordAuthenticationToken(userDetails, null, authorities);
               // SecurityContextHolder.getContext().setAuthentication(authentication);
                


                
                //Registrar na sesão --- isso aqui garante o registro nas proximas requisições 
                SecurityContext context = SecurityContextHolder.createEmptyContext();
                //O contexto e configurado com a autenticação 
                context.setAuthentication(authentication);
                SecurityContextHolder.setContext(context);

                //Salvando o contexto de segurança na sesão 
                HttpSession session = request.getSession(true);
                session.setAttribute(
                    HttpSessionSecurityContextRepository.SPRING_SECURITY_CONTEXT_KEY,
                    context
                );

       
            return ResponseEntity.ok("Authorized");
            }

        }

       
        return ResponseEntity.status(401).body("User or Password invalid");        
    } 


}
