package com.manager.Merum.repository.c2server;

import com.manager.Merum.model.entity.c2Server.AutomationConfig;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.List;

public interface AutomationConfigRepository extends JpaRepository<AutomationConfig, Long> {

    List<AutomationConfig> findByServerId(Long serverId);
}
