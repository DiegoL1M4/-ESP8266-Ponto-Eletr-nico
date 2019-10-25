package com.pontoeletronico.controller;

import java.time.LocalDateTime;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import com.pontoeletronico.entities.Data;
import com.pontoeletronico.repository.GeneralSetupRepository;

@RestController
@RequestMapping("general")
public class GeneralController {
	
	@Autowired
	private GeneralSetupRepository generalSetupRepository;
	
	@GetMapping("nome")
	public String nome() {
		return generalSetupRepository.findByNome("nome_empresa").getValor();
	}
	
	@GetMapping("data")
	public Data data() {
		LocalDateTime dataDb = LocalDateTime.now();
		int weekDay = dataDb.getDayOfWeek().getValue() + 1;

		Data data = new Data(dataDb.getHour(),
							 dataDb.getMinute(),
							 dataDb.getSecond(),
							 weekDay,
							 dataDb.getDayOfMonth(),
							 dataDb.getMonthValue(),
							 dataDb.getYear());
		
		return data;
	}

}
