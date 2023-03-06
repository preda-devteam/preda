import React, { useEffect, useState, useCallback } from "react";
import { MemoryRouter as Router, Switch } from "react-router-dom";

import { routes } from "./routes/config";
import { MessagesContext, MenuContext } from "./context";
import { RouteWithSubRoutes } from "./routes/RouteWithSubRoutes";

export const App = () => {
  const [messagesFromExtension, setMessagesFromExtension] = useState<string[]>(
    []
  );
  const [menu, changeMenu] = useState<string>("block");

  useEffect(() => {}, []);

  return (
    <Router initialEntries={["/"]}>
      <MenuContext.Provider value={menu}>
        <MessagesContext.Provider value={messagesFromExtension}>
          <div>
            <Switch>
              {routes.map((route, i) => (
                <RouteWithSubRoutes key={i} {...route} />
              ))}
            </Switch>
          </div>
        </MessagesContext.Provider>
      </MenuContext.Provider>
    </Router>
  );
};
