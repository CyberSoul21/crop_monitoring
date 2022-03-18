import { Component, OnInit } from '@angular/core';
import { CultivodbService } from './../../services/cultivodb.service'; //api REST
import { DatoPlanta } from './../../interfaces/dato-planta';

@Component({
  selector: 'app-action-sheet',
  templateUrl: './action-sheet.page.html',
  styleUrls: ['./action-sheet.page.scss'],
})
export class ActionSheetPage implements OnInit {

  constructor() { }

  ngOnInit() {
  }

}
