package com.manager.Merum.repository.c2server;

import com.manager.Merum.model.entity.c2Server.SecurityConfig;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.Optional;

public interface SecurityConfigRepository extends JpaRepository<SecurityConfig, Long> {

    Optional<SecurityConfig> findByServerId(Long serverId);
}
