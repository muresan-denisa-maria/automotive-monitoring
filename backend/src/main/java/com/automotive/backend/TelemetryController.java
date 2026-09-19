package com.automotive.backend;

import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class TelemetryController {

    @PostMapping("/telemetry")
    public ResponseEntity<String> receiveTelemetry(
            @RequestBody String telemetryJson
    ) {
        System.out.println("Telemetry received:");
        System.out.println(telemetryJson);

        return ResponseEntity.ok(
                "Telemetry received successfully\n"
        );
    }
}