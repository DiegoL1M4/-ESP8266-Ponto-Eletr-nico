package com.pontoeletronico.repository;

import org.springframework.data.jpa.repository.JpaRepository;

import com.pontoeletronico.entities.Usuario;

public interface UsuarioRepository extends JpaRepository<Usuario, Long> {

	Usuario findByTagRFID(String tagRFID);
	
}
