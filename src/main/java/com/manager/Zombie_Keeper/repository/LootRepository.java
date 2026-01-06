package com.manager.Zombie_Keeper.repository;

import org.springframework.data.jpa.repository.JpaRepository;

import com.manager.Zombie_Keeper.model.entity.Loot;

import java.util.UUID;

public interface LootRepository extends JpaRepository<Loot, UUID> {

}
