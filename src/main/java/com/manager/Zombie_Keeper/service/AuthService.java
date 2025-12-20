package com.manager.Zombie_Keeper.service;

import org.springframework.security.access.AccessDeniedException;
import org.springframework.security.authentication.AuthenticationCredentialsNotFoundException;
import org.springframework.security.core.Authentication;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.stereotype.Service;

import com.manager.Zombie_Keeper.model.CustomUserDetails;
import com.manager.Zombie_Keeper.model.User;

@Service
public class AuthService {

    public User getAuthUser(){

        Authentication auth = SecurityContextHolder.getContext().getAuthentication();


        if(auth != null && !auth.isAuthenticated() ){

            throw new AuthenticationCredentialsNotFoundException("User not found");
        }


        Object pricipal = auth.getPrincipal();

        if(pricipal instanceof CustomUserDetails cud){

            return cud.getUser();
        }

        throw new AccessDeniedException(null, null);

    }

}
