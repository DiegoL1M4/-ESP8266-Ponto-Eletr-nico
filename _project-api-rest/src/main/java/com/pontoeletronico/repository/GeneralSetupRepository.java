package com.pontoeletronico.repository;

import org.springframework.data.jpa.repository.JpaRepository;

import com.pontoeletronico.entities.Generalsetup;

public interface GeneralSetupRepository extends JpaRepository<Generalsetup, Long> {
	
	public Generalsetup findByNome(String nome);

}
