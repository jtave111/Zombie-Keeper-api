package com.manager.Merum.repository.c2server;

import com.manager.Merum.model.entity.c2Server.WebConfig;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.Optional;

public interface WebConfigRepository extends JpaRepository<WebConfig, Long> {

    Optional<WebConfig> findByServerId(Long serverId);
}
