package com.manager.Zombie_Keeper.controller.localNetwork;

import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.http.MediaType;

import com.manager.Zombie_Keeper.model.entity.localNetwork.NetworkNode;
import com.manager.Zombie_Keeper.model.entity.localNetwork.NetworkSession;
import com.manager.Zombie_Keeper.model.entity.localNetwork.Port;
import com.manager.Zombie_Keeper.repository.localNetwork.NetworkSessionRepository;
import com.manager.Zombie_Keeper.service.localNetwork.fingerprint.LocalNetworkFingerprintService;

import tools.jackson.databind.ObjectMapper;

@RestController
@RequestMapping("/c2-server/local-network/recon")
public class ReconController {

    LocalNetworkFingerprintService localNetFp;
    NetworkSessionRepository sessionRepository;


    public ReconController(LocalNetworkFingerprintService localNetFp, NetworkSessionRepository sessionRepository ){
        this.localNetFp = localNetFp;
        this.sessionRepository = sessionRepository;
    }
    
    /*
    *  use sec usec for struct timeval(c++) non-bloking io configuration
    *  Ex: "LocalFingerPrint", "all or any ", "0", "300000"
    */
    @GetMapping(value = "/session/{binaryName}/{flag}/{sec}/{usec}", produces = MediaType.APPLICATION_JSON_VALUE)
    public ResponseEntity<String> sessionRecon(@PathVariable String binaryName, @PathVariable String flag, @PathVariable String sec, @PathVariable String usec){

        String json = localNetFp.excLocalNetFingerPrint(binaryName, flag, sec, usec);

        System.out.printf("JSON output for flag: %s: %s ", flag, json);

        try {
            ObjectMapper mapper = new ObjectMapper();

            NetworkSession sessionEntity = mapper.readValue(json, NetworkSession.class);

            if(sessionEntity.getDevices() != null){

                for (NetworkNode n : sessionEntity.getDevices()) {
                    n.setNetwork(sessionEntity);

                    if(n.getOpenPorts() != null){

                        for(Port p: n.getOpenPorts()){
                            p.setNode(n);

                        }
                    }

                }
            }

            sessionRepository.save(sessionEntity);

        } catch (Exception e) {

            System.out.println("Error " +  e.getMessage());
            // TODO: handle exception
        }

        return ResponseEntity.ok(json);
    }  


}
