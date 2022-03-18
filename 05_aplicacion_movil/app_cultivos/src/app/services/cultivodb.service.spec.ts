import { TestBed } from '@angular/core/testing';

import { CultivodbService } from './cultivodb.service';

describe('CultivodbService', () => {
  beforeEach(() => TestBed.configureTestingModule({}));

  it('should be created', () => {
    const service: CultivodbService = TestBed.get(CultivodbService);
    expect(service).toBeTruthy();
  });
});
