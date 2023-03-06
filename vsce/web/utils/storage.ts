export const ssGetItem = (key: string): string | number | null => {
  let data: string | null = sessionStorage.getItem(key);
  try {
    data = JSON.parse(data as string);
  } catch (e) {}
  return data;
};

export const ssSetItem = (key: string, data: any) => {
  if (typeof data === 'object' && !(data instanceof String)) {
    data = JSON.stringify(data);
  }
  try {
    sessionStorage.setItem(key, data);
  } catch (e) {
    return false;
  }
  return true;
};

export const ssRemoveItem = (key: string) => {
  try {
    sessionStorage.removeItem(key);
  } catch (e) {
    return false;
  }
  return true;
};

export const lsGetItem = (key: string): any => {
  let data: string | null = localStorage.getItem(key);
  try {
    data = JSON.parse(data as string);
  } catch (e) {}
  return data;
};

export const lsSetItem = (key: string, data: any): boolean => {
  if (typeof data === 'object' && !(data instanceof String)) {
    data = JSON.stringify(data);
  }
  try {
    localStorage.setItem(key, data);
  } catch (e) {
    return false;
  }
  return true;
};

export const lsRemoveItem = (key: string) => {
  try {
    localStorage.removeItem(key);
  } catch (e) {
    return false;
  }
  return true;
};
