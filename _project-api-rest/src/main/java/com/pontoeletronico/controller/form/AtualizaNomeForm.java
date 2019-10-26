package com.pontoeletronico.controller.form;

import javax.validation.constraints.NotNull;

import com.pontoeletronico.entities.Generalsetup;
import com.pontoeletronico.repository.GeneralSetupRepository;

public class AtualizaNomeForm {
	
	@NotNull
	private String valor;

	public AtualizaNomeForm() { }

	public String getValor() {
		return valor;
	}

	public void setValor(String valor) {
		this.valor = valor;
	}

	public Generalsetup atualizar(Long id, GeneralSetupRepository generalSetupRepository) {
		Generalsetup setup = generalSetupRepository.getOne(id);
		
		setup.setValor(this.valor);
		
		return setup;
	}
	
}
