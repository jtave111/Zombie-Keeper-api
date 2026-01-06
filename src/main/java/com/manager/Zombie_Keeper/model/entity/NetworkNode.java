package com.manager.Zombie_Keeper.model.entity;



import java.util.ArrayList;
import java.util.List;

import com.manager.Zombie_Keeper.model.embeddable.Ports;
import com.manager.Zombie_Keeper.model.embeddable.Vulnerability;

import jakarta.persistence.CollectionTable;

import jakarta.persistence.ElementCollection;
import jakarta.persistence.Entity;
import jakarta.persistence.FetchType;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;
import jakarta.persistence.JoinColumn;
import jakarta.persistence.ManyToOne;

@Entity
public class NetworkNode {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    private String ipAddress;
    private String macAddress;
    private String hostname;
    private String vendor;

    private boolean isTrusted;
    private int vunerabilityScore;
    
    @ElementCollection(fetch = FetchType.EAGER)
    @CollectionTable(
        name = "tb_node_ports", 
        joinColumns = @JoinColumn(name= "node_id")
    )
    private List<Ports> openPorts = new ArrayList<>();


    @ElementCollection(fetch = FetchType.LAZY)
    @CollectionTable(
        name = "tb_node_vulns",
        joinColumns = @JoinColumn(name = "node_id")
    )
    private List<Vulnerability> vulnerabilities = new ArrayList<>();


    @ManyToOne
    @JoinColumn(name = "network_id")
    private NetworkSession network;





    public Long getId() {
        return id;
    }


    public void setId(Long id) {
        this.id = id;
    }

    public List<Ports> getOpenPorts() {
        return openPorts;
    }

    public void setOpenPorts(List<Ports> openPorts) {
        this.openPorts = openPorts;
    }

    public String getIpAddress() {
        return ipAddress;
    }


    public void setIpAddress(String ipAddress) {
        this.ipAddress = ipAddress;
    }


    public String getMacAddress() {
        return macAddress;
    }


    public void setMacAddress(String macAddress) {
        this.macAddress = macAddress;
    }


    public String getHostname() {
        return hostname;
    }


    public void setHostname(String hostname) {
        this.hostname = hostname;
    }


    public String getVendor() {
        return vendor;
    }


    public void setVendor(String vendor) {
        this.vendor = vendor;
    }


    public boolean isTrusted() {
        return isTrusted;
    }


    public void setTrusted(boolean isTrusted) {
        this.isTrusted = isTrusted;
    }


    public int getVunerabilityScore() {
        return vunerabilityScore;
    }


    public void setVunerabilityScore(int vunerabilityScore) {
        this.vunerabilityScore = vunerabilityScore;
    }

    public NetworkSession getNetwork() {
        return network;
    }


    public void setNetwork(NetworkSession network) {
        this.network = network;
    }
}
