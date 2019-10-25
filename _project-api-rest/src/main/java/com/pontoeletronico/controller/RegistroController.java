package com.pontoeletronico.controller;

import java.net.URI;
import java.time.LocalDateTime;
import java.util.List;

import javax.transaction.Transactional;
import javax.validation.Valid;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.util.UriComponentsBuilder;

import com.pontoeletronico.controller.form.RegistroForm;
import com.pontoeletronico.entities.Registro;
import com.pontoeletronico.repository.RegistroRepository;

@RestController
@RequestMapping("registro")
public class RegistroController {
	@Autowired
	private RegistroRepository registroRepository;
	
	@GetMapping
	public List<Registro> lista() {
		return registroRepository.findAll();
	}
	
	@PostMapping
	@Transactional
	public ResponseEntity<Registro> cadastrar(@RequestBody @Valid RegistroForm form, UriComponentsBuilder uriBuilder) {
		long contReg = registroRepository.countByDataAndTagRfid(LocalDateTime.now(), form.getTagRFID());
		
		if(contReg < 4) {
			Registro register = new Registro(form.getTagRFID(), contReg + 1, form.getData());
			registroRepository.save(register);
			
			URI uri = uriBuilder.path("/registro/{id}").buildAndExpand(register.getId_registro()).toUri();
			return ResponseEntity.created(uri).body(register);
		}
		
		return ResponseEntity.badRequest().body(new Registro());
		
		
	}
}
