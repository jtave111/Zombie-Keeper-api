package com.manager.Merum.repository.c2server;

import com.manager.Merum.model.entity.c2Server.ApiConfig;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.Optional;

public interface ApiConfigRepository extends JpaRepository<ApiConfig, Long> {

    Optional<ApiConfig> findByPortId(Long portId);
}
