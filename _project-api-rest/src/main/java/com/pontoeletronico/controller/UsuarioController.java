package com.pontoeletronico.controller;

import java.net.URI;
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

import com.pontoeletronico.controller.form.UsuarioForm;
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
		Usuario user = new Usuario(form.getNome(), form.getTagRFID());
		usuarioRepository.save(user);
		
		URI uri = uriBuilder.path("/usuario/{id}").buildAndExpand(user.getId_usuario()).toUri();
		return ResponseEntity.created(uri).body(user);
	}
}
