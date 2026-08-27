package com.manager.Merum.repository.c2server;

import com.manager.Merum.model.entity.c2Server.NetworkConfig;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.List;

public interface NetworkConfigRepository extends JpaRepository<NetworkConfig, Long> {

    List<NetworkConfig> findByServerId(Long serverId);
}
