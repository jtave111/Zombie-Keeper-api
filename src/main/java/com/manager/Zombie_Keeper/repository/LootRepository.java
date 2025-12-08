package com.manager.Zombie_Keeper.repository;

import com.manager.Zombie_Keeper.model.Loot;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.UUID;

public interface LootRepository extends JpaRepository<Loot, UUID> {

}
