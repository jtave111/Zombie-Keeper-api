package com.manager.Zombie_Keeper.repository;

import org.springframework.data.jpa.repository.JpaRepository;

import com.manager.Zombie_Keeper.model.entity.NetworkNode;

public interface NetworkNodeRepository extends JpaRepository <NetworkNode, Long> {
    
    
}
