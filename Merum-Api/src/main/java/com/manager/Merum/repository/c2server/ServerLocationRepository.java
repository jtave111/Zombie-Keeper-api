package com.manager.Merum.repository.c2server;

import com.manager.Merum.model.entity.c2Server.ServerLocation;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.List;

public interface ServerLocationRepository extends JpaRepository<ServerLocation, Long> {

    List<ServerLocation> findByServerId(Long serverId);
}
