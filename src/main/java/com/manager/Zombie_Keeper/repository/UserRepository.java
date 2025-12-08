package com.manager.Zombie_Keeper.repository;

import java.util.Optional;

import org.springframework.data.jpa.repository.JpaRepository;

import com.manager.Zombie_Keeper.model.User;

public interface UserRepository extends JpaRepository<User, Long > {
    
   Optional<User> findByUsername(String username);
}
