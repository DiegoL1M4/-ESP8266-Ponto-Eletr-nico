package com.pontoeletronico.controller;

import java.net.URI;
import java.util.List;
import java.util.Optional;

import javax.transaction.Transactional;
import javax.validation.Valid;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.PutMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.util.UriComponentsBuilder;

import com.pontoeletronico.controller.form.AtualizaNomeForm;
import com.pontoeletronico.controller.form.UsuarioForm;
import com.pontoeletronico.entities.Generalsetup;
import com.pontoeletronico.entities.Usuario;
import com.pontoeletronico.repository.UsuarioRepository;

@RestController
@RequestMapping("usuario")
public class UsuarioController {
	
	@Autowired
	private UsuarioRepository usuarioRepository;
	
	@GetMapping
	public List<Usuario> lista() {
		return usuarioRepository.findAll();
	}
	
	@PostMapping
	@Transactional
	public ResponseEntity<Usuario> cadastrar(@RequestBody @Valid UsuarioForm form, UriComponentsBuilder uriBuilder) {
		Usuario userTest = usuarioRepository.findByTagRFID(form.getTagRFID());
		
		if(userTest == null) {
			Usuario user = new Usuario(form.getNome(), form.getTagRFID());
			usuarioRepository.save(user);
			
			URI uri = uriBuilder.path("/usuario/{id}").buildAndExpand(user.getId_usuario()).toUri();
			return ResponseEntity.created(uri).body(user);
		}
		return ResponseEntity.status(700).body(new Usuario());

	}
	
	/*
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
	*/
}
