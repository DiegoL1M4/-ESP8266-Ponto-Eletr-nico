package com.pontoeletronico.repository;

import java.time.LocalDateTime;

import org.springframework.data.jpa.repository.JpaRepository;

import com.pontoeletronico.entities.Registro;

public interface RegistroRepository extends JpaRepository<Registro, Long> {

	long countByDataAndTagRfid(LocalDateTime data, String tagRfid);
	
}
