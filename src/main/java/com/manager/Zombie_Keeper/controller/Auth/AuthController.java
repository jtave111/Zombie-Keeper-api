package com.manager.Zombie_Keeper.controller.Auth;

import java.nio.file.AccessDeniedException;
import java.util.Collection;
import java.util.Optional;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
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

import com.manager.Zombie_Keeper.dtos.CreateAcRequest;
import com.manager.Zombie_Keeper.dtos.LoginRequest;
import com.manager.Zombie_Keeper.model.entity.auth.Role;
import com.manager.Zombie_Keeper.model.entity.auth.User;
import com.manager.Zombie_Keeper.repository.auth.RoleRepository;
import com.manager.Zombie_Keeper.repository.auth.UserRepository;

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
    @Autowired
    private RoleRepository roleRepository;

    User userLogged;

    @PostMapping("/login")
    public ResponseEntity<String> login(@RequestBody @Valid LoginRequest dto, HttpServletRequest request){
       
       Optional<User> userOptional = userRepository.findByUsername(dto.getUsername());
       
       System.out.println(">>> Requeste for user: " + dto.getUsername());

        if(userOptional.isPresent()){

            User user = userOptional.get();

            if(encoder.matches(dto.getPassword(), user.getPassword())){
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

                userLogged = userOptional.get();
       
            return ResponseEntity.ok("Authorized");
            }

        }

       
        return ResponseEntity.status(401).body("User or Password invalid");        
    } 


    @PostMapping("/register")
    public ResponseEntity<String> createAccount(@RequestBody @Valid CreateAcRequest dto) throws AccessDeniedException{
        //Acesso ao contexto de usuario que foi salvo no login
        Authentication auth = SecurityContextHolder.getContext().getAuthentication();

        if(auth == null || !auth.isAuthenticated()){

            throw new AccessDeniedException("Not authenticated");
        
        }

        User userSec  = (User) auth.getPrincipal();
        

        String roleLogged = userSec.getRole().getType();
        if (!roleLogged.equals("ADMIN")) {
            throw new AccessDeniedException("Access denied");                
        }
    
        
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
            
            return ResponseEntity.status(HttpStatus.CREATED).body(" User created");
        }         
        
              
        return ResponseEntity.status(401).body("User not created");

    }


}
