package com.manager.Zombie_Keeper.model.entity;

import java.time.LocalDateTime;
import java.util.List;
import java.util.UUID;

import jakarta.persistence.CascadeType;
import jakarta.persistence.Column;
import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;
import jakarta.persistence.OneToMany;

@Entity
public class NetworkSession {

    @Id
    @GeneratedValue(strategy = GenerationType.UUID)
    private UUID id;
    //Mac gateway or SSID + BSSID
    @Column(nullable = false, length = 700)
    private String networkIdentifier;

    private String gatewayIp;
    private String subnetMask;


    private LocalDateTime fristSeen;
    private LocalDateTime lastSeen;

    @OneToMany(mappedBy = "network", cascade = CascadeType.ALL)    
    private List<NetworkNode> devices;


    private String cidr;

    public String getCidr() {
        return cidr;
    }

    public void setCidr(String cidr) {
        this.cidr = cidr;
    }

    public UUID getId() {
        return id;
    }

    public void setId(UUID id) {
        this.id = id;
    }

    public String getNetworkIdentifier() {
        return networkIdentifier;
    }

    public void setNetworkIdentifier(String networkIdentifier) {
        this.networkIdentifier = networkIdentifier;
    }

    public String getGatewayIp() {
        return gatewayIp;
    }

    public void setGatewayIp(String gatewayIp) {
        this.gatewayIp = gatewayIp;
    }

    public String getSubnetMask() {
        return subnetMask;
    }

    public void setSubnetMas(String subnetMask) {
        this.subnetMask = subnetMask;
    }

    public LocalDateTime getFristSeen() {
        return fristSeen;
    }

    public void setFristSeen(LocalDateTime fristSeen) {
        this.fristSeen = fristSeen;
    }

    public LocalDateTime getLastSeen() {
        return lastSeen;
    }

    public void setLastSeen(LocalDateTime lastSeen) {
        this.lastSeen = lastSeen;
    }

    public List<NetworkNode> getDevices() {
        return devices;
    }

    public void setDevices(List<NetworkNode> devices) {
        this.devices = devices;
    }





}
