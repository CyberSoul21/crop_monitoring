import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';

import { DatoPlanta } from './../interfaces/dato-planta';

@Injectable({
  providedIn: 'root'
})
export class CultivodbService {

  private api = 'http://mynodered.ddns.net:1880'

  constructor(
  	  	private http: HttpClient
) { }

arregloPlantas() { //api REST
  	const path = `${this.api}/monitoreo2`;
  	return this.http.get<DatoPlanta[]>(path);
  }
}
