package com.pontoeletronico.controller;

import java.time.LocalDateTime;
import java.util.Optional;

import javax.transaction.Transactional;
import javax.validation.Valid;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PutMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import com.pontoeletronico.controller.form.AtualizaNomeForm;
import com.pontoeletronico.entities.Data;
import com.pontoeletronico.entities.Generalsetup;
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
	
	@PutMapping("nome/{id}")
	@Transactional
	public ResponseEntity<Generalsetup> atualizarNome(@PathVariable Long id, @RequestBody @Valid AtualizaNomeForm form) {
		Optional<Generalsetup> optional = generalSetupRepository.findById(id);
		if (optional.isPresent()) {
			Generalsetup nome = form.atualizar(id, generalSetupRepository);
			return ResponseEntity.ok(nome);
		}
		
		return ResponseEntity.notFound().build();
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
