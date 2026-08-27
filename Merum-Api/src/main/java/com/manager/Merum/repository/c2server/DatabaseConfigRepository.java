package com.manager.Merum.repository.c2server;

import com.manager.Merum.model.entity.c2Server.DatabaseConfig;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.List;

public interface DatabaseConfigRepository extends JpaRepository<DatabaseConfig, Long> {

    List<DatabaseConfig> findByServerId(Long serverId);
}
