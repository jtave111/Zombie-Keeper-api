package com.manager.Zombie_Keeper.model.entity.localNetwork;


import java.util.ArrayList;
import java.util.List;
import jakarta.persistence.*;


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
    
    @OneToMany(mappedBy = "node", cascade = CascadeType.ALL, orphanRemoval = true)
    private List<Port> openPorts = new ArrayList<>();

    @OneToMany(mappedBy = "node", cascade = CascadeType.ALL, orphanRemoval = true)
    private List<Vulnerability> vulnerabilities = new ArrayList<>();

    @ManyToOne
    @JoinColumn(name = "network_id")
    private NetworkSession network;


    public void addPort(Port port ){
        openPorts.add(port);
        port.setNode(this);
        
    }
    public void deletePort(Port port){
        openPorts.remove(port);
        port.setNode(null);

    }
    
    public void addVulnerability(Vulnerability vuln) {
        vulnerabilities.add(vuln);
        vuln.setNode(this);
    }

    public void removeVulnerability(Vulnerability vuln) {
        vulnerabilities.remove(vuln);
        vuln.setNode(null);
    }

    public Long getId() {
        return id;
    }


    public void setId(Long id) {
        this.id = id;
    }

    public List<Port> getOpenPorts() {
        return openPorts;
    }

    public void setOpenPorts(List<Port> openPorts) {
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
