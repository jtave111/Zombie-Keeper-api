package com.manager.Zombie_Keeper.controller.localNetwork;

import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import com.manager.Zombie_Keeper.service.localNetwork.fingerprint.LocalNetworkFingerprintService;

@RestController
@RequestMapping("/c2-server/local-network/Recon")
public class ReconController {

    LocalNetworkFingerprintService localNetFp;

    public ReconController(LocalNetworkFingerprintService localNetFp ){
        this.localNetFp = localNetFp;
    }
    
    @GetMapping(produces = org.springframework.http.MediaType.APPLICATION_JSON_VALUE)
    public ResponseEntity<String> getCompleteRecom(){
        // --> sec, usec for struct timeval(c++) non-bloking io configuration
        String reconSession = localNetFp.excLocalNetFingerPrint("LocalFingerPrint", "all", "0", "300000");
        
        return ResponseEntity.ok(reconSession);
    }

}
