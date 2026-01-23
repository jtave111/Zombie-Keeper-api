package com.manager.Zombie_Keeper.controller.localNetwork;

import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.http.MediaType;
import com.manager.Zombie_Keeper.service.localNetwork.fingerprint.LocalNetworkFingerprintService;

@RestController
@RequestMapping("/c2-server/local-network/recon")
public class ReconController {

    LocalNetworkFingerprintService localNetFp;

    public ReconController(LocalNetworkFingerprintService localNetFp ){
        this.localNetFp = localNetFp;
    }
    
    /*
    *  use sec usec for struct timeval(c++) non-bloking io configuration
    *  Ex: "LocalFingerPrint", "all or any ", "0", "300000"
    */
    @GetMapping(value = "/session/{binaryName}/{flag}/{sec}/{usec}", produces = MediaType.APPLICATION_JSON_VALUE)
    public ResponseEntity<String> sessionRecon(@PathVariable String binaryName, @PathVariable String flag, @PathVariable String sec, @PathVariable String usec){

        String json = localNetFp.excLocalNetFingerPrint(binaryName, flag, sec, usec);

        System.out.printf("JSON output for flag: %s: %s ", flag, json);

        return ResponseEntity.ok(json);
    }  


}
