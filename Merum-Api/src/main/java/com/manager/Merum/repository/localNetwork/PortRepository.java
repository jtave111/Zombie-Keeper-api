package com.manager.Merum.repository.localNetwork;

import java.util.Optional;

import org.springframework.data.jpa.repository.JpaRepository;

import com.manager.Merum.model.entity.localNetwork.Port;

public interface PortRepository extends JpaRepository<Port, Long> {

    Optional<Integer> findByNumber(Integer portNumber);
}
