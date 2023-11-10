import dayjs from 'dayjs';
import utc from 'dayjs/plugin/utc';
dayjs.extend(utc);

export function mapToStringArray(obj: any): string[] {
  let ret: string[] = [];
  for (const p in obj) {
    if (obj.hasOwnProperty(p)) {
      const value = obj[p];
      ret.push(p, typeof value === 'object' ? JSON.stringify(value) : value);
    }
  }
  return ret;
}

export function trimEndSlash(url: string) {
  return url.replace(/(\/+)$/, '');
}

export function toShard(value: string | number, order: string, withUnit = true) {
  const unit = withUnit ? '#' : '';
  return unit + (String(value) === '65535' ? 'g' : String(value).replace('#', '')) + ((value.toString()).match('g') ? '' : ('/' + 2 ** Number(order || 0)))
}
export const toUTCTime = (time: number | string | undefined) => {
  if (!time) {
    return '';
  }
  return dayjs(time).utc().format('YYYY/MM/DD HH:mm') + ' (UTC)';
};

export const toPrettyNumber = (value: number | string) => {
  if (typeof value === 'string') {
    value = parseFloat(value);
  }
  return value.toLocaleString();
};

export const toDeployFlag = (flag: string) => {
  if (!flag) {
    return '';
  }
  return flag.split('|').join(' | ');
};