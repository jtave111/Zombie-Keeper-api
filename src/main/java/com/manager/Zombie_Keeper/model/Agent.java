
package com.manager.Zombie_Keeper.model;

import jakarta.persistence.*;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Set;
import java.util.UUID;

import com.manager.Zombie_Keeper.model.enums.Flags;
import com.manager.Zombie_Keeper.model.enums.Tags;




@Entity
public class Agent {

    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private UUID id;

    private String hostname;

    private String os;

    private LocalDateTime lastSeen;

    @OneToMany(mappedBy = "agent", cascade = CascadeType.ALL)
    private List<Loot> loots = new ArrayList<>();

    private String ip;

    @Column(length = 500)
    private Set<Flags> flags;
    
    @Column(length = 500)
    private Set<Tags> tags;

    public Agent(){

    }

    @PrePersist
    public void onCreate(){
        this.lastSeen =LocalDateTime.now();
        
    }

    public Set<Tags> getTags(){
        return tags;
    }

    public void setTgas(Set<Tags> tags){

        this.tags = tags;

    }

    public Set<Flags> getFlags(){
       
        return flags;
    }

    public void setFlags(Set<Flags> flags){
        this.flags = flags;
    }
    
    public String getIp() {
        return ip;
    }

    public void setIp(String ip) {
        this.ip = ip;
    }

    public UUID getId() {
        return id;
    }

    public void setId(UUID id) {
        this.id = id;
    }

    public String getHostname() {
        return hostname;
    }

    public void setHostname(String hostname) {
        this.hostname = hostname;
    }

    public String getOs() {
        return os;
    }

    public void setOs(String os) {
        this.os = os;
    }

    public LocalDateTime getLastSeen() {
        return lastSeen;
    }

    public void setLastSeen(LocalDateTime lastSeen) {
        this.lastSeen = lastSeen;
    }

    public List<Loot> getLoots() {
        return loots;
    }

    public void setLoots(List<Loot> loots) {
        this.loots = loots;
    }

}
