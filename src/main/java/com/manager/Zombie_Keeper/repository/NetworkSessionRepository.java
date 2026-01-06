package com.manager.Zombie_Keeper.repository;

import java.util.UUID;

import org.springframework.data.jpa.repository.JpaRepository;

import com.manager.Zombie_Keeper.model.entity.NetworkSession;

public interface NetworkSessionRepository extends JpaRepository<NetworkSession, UUID> {
    
}
