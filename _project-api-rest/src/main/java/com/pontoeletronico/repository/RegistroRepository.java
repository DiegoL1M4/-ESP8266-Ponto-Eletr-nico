package com.pontoeletronico.repository;

import org.springframework.data.jpa.repository.JpaRepository;

import com.pontoeletronico.entities.Registro;

public interface RegistroRepository extends JpaRepository<Registro, Long> {

}
