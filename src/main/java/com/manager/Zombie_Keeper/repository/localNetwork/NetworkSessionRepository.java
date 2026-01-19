package com.manager.Zombie_Keeper.repository.localNetwork;

import java.util.UUID;

import org.springframework.data.jpa.repository.JpaRepository;

import com.manager.Zombie_Keeper.model.entity.localNetwork.NetworkSession;

public interface NetworkSessionRepository extends JpaRepository<NetworkSession, UUID> {
    
}
