import React from 'react';
import { Home } from '../pages/Home';

export type RouteConfigComponentProps = Pick<RouteConfig, 'routes'>;

export type RouteConfig = {
  path: string;
  component: React.ComponentType<RouteConfigComponentProps>;
  exact?: boolean;
  routes?: RouteConfig[];
};

export const routes: RouteConfig[] = [
  {
    path: '/',
    component: Home,
    exact: true,
  },
];
