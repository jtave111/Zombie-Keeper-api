package com.manager.Merum.repository.agent;

import org.springframework.data.jpa.repository.JpaRepository;

import com.manager.Merum.model.entity.agent.Loot;

import java.util.UUID;

public interface LootRepository extends JpaRepository<Loot, UUID> {

}
