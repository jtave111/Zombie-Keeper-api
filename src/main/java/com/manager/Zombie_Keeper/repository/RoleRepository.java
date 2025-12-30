package com.manager.Zombie_Keeper.repository;


import org.springframework.data.jpa.repository.JpaRepository;

import com.manager.Zombie_Keeper.model.Role;

public interface RoleRepository extends JpaRepository<Role, Long> {
    
    Role findByType(String type);
   
}
