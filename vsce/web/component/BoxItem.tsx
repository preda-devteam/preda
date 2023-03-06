import { toDeployFlag, toPrettyNumber, toShard, toUTCTime } from '@/utils/strings';
import ReactJson from "@dioxide-js/react-json-view";
import * as React from 'react'
import MoreSwitch from './MoreSwitch'
import AddressText from './AddressText'
import clss from 'classnames'
import Tooltip from './Tooltip';

const ContractState = (s: any) => {
  return (
    <div className='state-item'>
      <div className='box-key'>Contract:</div>
      <div className='box-val'>{s.Contract}</div>
      <div className='box-key'>State:</div>
      <div className='box-val'>
        <ReactJson
          src={(s.State as object)}
          style={{ background: "none" }}
          displayObjectSize={false}
          enableClipboard={false}
          displayDataTypes={false}
          displayArrayKey={false}
          collapsed={false}
          name={false}
          theme="chalk"
        />
      </div>
    </div>
  )
}

type BoxItemType = {
  data: any, 
  key: string, 
  title: string,
  shardOrder?: string
}

type ProfingType = {
  BlockHeight: number
  ShardIndex: string
  TxnCount: number
  TPS: number
}

export const DeployBox = ({data, key, title}: BoxItemType) => {
  const [more, setMore] = React.useState<boolean>(false)

  const originData = React.useMemo(() => {
    return  more ? data : data[0] ? [data[0]] : [];
  }, [data, more]);

  return !originData.length ? null : (
    <div className="box deploy-box" key={key}>
      <p className="box-title">{title}</p>
      {originData.map((d: any) => (
        <div className="box-content" key={d.source + d.contract}>
          <div className="deploy-header">
              <div className='deploy-header-item'>
                <p className="box-key">Source</p>
                <p className="box-val">{d.source}</p>
              </div>
              <div className='deploy-header-item'>
                <p className="box-key">Contract</p>
                <p className="box-val">{d.contract}</p>
              </div>
              <div className='deploy-header-item'>
                <p className="box-key">Engine</p>
                <p className="box-val">{d.engine}</p>
              </div>
          </div>
          {
            d.structs && d.structs.length
              ? <div className='deploy-item'>
                  <p className='deploy-title'>Structs</p>
                  {d.structs.map((struct: Struct) => (
                    <div className='struct-item' key={struct.name}>
                      <p className='deploy-name'>{struct.name}</p>
                      <div className='view-table'>
                        <table>
                          <thead>
                            <tr>
                              <th>Identifier</th>
                              <th>DataType</th>
                            </tr>
                          </thead>
                          <tbody>
                            {(struct.layout || []).map(layoutItem => (
                              <tr key={struct.name + layoutItem.identifier}>
                                <td width="320">{layoutItem.identifier}</td>
                                <td>{layoutItem.dataType}</td>
                              </tr>
                            ))}
                          </tbody>
                        </table>
                      </div>
                    </div>
                  ))}
                </div>
              : null
          }
          {
            d.enumerators && d.enumerators.length
              ? <div className='deploy-item'>
                  <p className='deploy-title'>ENumerators</p>
                  {d.enumerators.map((enumerator: Enumerator) => (
                    <div className='struct-item' key={enumerator.name}>
                      <p className='deploy-name'>{enumerator.name}</p>
                      <div className='view-table'>
                        <div className='deploy-enumerator'> [{(enumerator.value || []).map(v => `"${v}"`).join(",")}] </div>
                      </div>
                    </div>
                  ))}
                </div>
              : null
          }
          <div className='deploy-item'>
            {
              Object.keys(d.scopes || {}).map(scope => {
                const scopeStates = (d.stateVariables || []).filter((state: StateVariable) => state.scope === scope) || [];
                const scopeFns = (d.functions || []).filter((fn: DeployFunction) => fn.scope === scope) || [];
                return (
                  <div className='deploy-scope'>
                    <p className='deploy-title'>{scope}</p>
                    <p className='deploy-name'>StateVariables</p>
                    <div className='view-table'>
                      <table>
                        <thead>
                          <tr>
                            <th>Name</th>
                            <th>DataType</th>
                          </tr>
                        </thead>
                        <tbody>
                          {scopeStates.map((stateItem: StateVariable) => (
                            <tr key={stateItem.name}>
                              <td width="320">{stateItem.name}</td>
                              <td>{stateItem.dataType}</td>
                            </tr>
                          ))}
                        </tbody>
                      </table>
                    </div>
                    <p className='deploy-name'>Functions</p>
                    <div className='view-table'>
                      <table>
                        <thead>
                          <tr>
                            <th>Name</th>
                            <th>Flag</th>
                            <th>Opcode</th>
                          </tr>
                        </thead>
                        <tbody>
                          {scopeFns.map((fn: DeployFunction) => (
                            <tr key={fn.name}>
                              <td width="320">{fn.name}</td>
                              <td>{toDeployFlag(fn.flag)}</td>
                              <td width="100">{fn.opcode}</td>
                            </tr>
                          ))}
                        </tbody>
                      </table>
                    </div>
                  </div>
                );
              })
            }
          </div>
        </div>
      ))}
      {data.length > 1 ? (
        <div className='center'>
          <MoreSwitch onChange={(s: boolean) => setMore(s)} value={more} />
        </div>
      ) : null}
    </div>
  )
};
export const AddrBox = ({data, key, title, shardOrder = '0'}: BoxItemType) => {
  const [more, setMore] = React.useState<boolean>(false)

  const originData = React.useMemo(() => {
    return  more ? data : data[0] ? [data[0]] : [];
  }, [data, more]);

  return !originData.length ? null : (
    <div className={clss({'mulit': originData.length > 1},"box addr-box")} key={key}>
      <p className="box-title">{title}</p>
        <div className="box-content" >
          <div>
            {originData.map((d: any) => (
              <div className='addr-item' key={d.Address}>
                  <div className="addr-header" >
                    Address:&nbsp;<AddressText addr={d.Address} addrIndex={d.AddressIndex} />
                  </div>
                  <div className='addr-shard'>
                    <div className='box-key'>Shard:</div>
                    <div className='box-val'>{toShard(d.ShardIndex,shardOrder)}</div>
                  </div>
                  <div className="addr-state"> 
                    {d.States.map((s: any) => (
                      <ContractState {...s} key={s.Contract} />
                    ))}
                  </div>
              </div>
            ))}
          </div>
          {data.length > 1 ? (
            <div className='center bottom'>
              <MoreSwitch onChange={(s: boolean) => setMore(s)} value={more} />
            </div>
          ) : null}
      </div>
    </div>
  )
};
export const ShardBox = ({data, key, title, shardOrder = '0'}: BoxItemType) => {
  const [more, setMore] = React.useState<boolean>(false)

  const originData = React.useMemo(() => {
    return  more ? data : data[0] ? [data[0]] : [];
  }, [data, more]);

  return !originData.length ? null : (
    <div className="box shard-box" key={key}>
      <p className="box-title">{title}</p>
        <div className="box-content" >
          <div>
            {originData.map((d: any) => (
              <div className='shard-item'  key={d.ShardIndex}>
                  <div className="shard-header">
                    Shard:&nbsp;{toShard(d.ShardIndex, shardOrder)}
                  </div>
                  <div className="shard-state"> 
                    {d.States.map((s: any) => (
                      <ContractState {...s} key={s.Contract} />
                    ))}
                  </div>
              </div>
            ))}
          </div>
          {data.length > 1 ? (
            <div className='center bottom'>
              <MoreSwitch onChange={(s: boolean) => setMore(s)} value={more} />
            </div>
          ) : null}
      </div>
    </div>
  );
};
export const TxnBox = ({data, key, title}: BoxItemType) => {
  const [more, setMore] = React.useState<boolean>(false)

  const originData = React.useMemo(() => {
    return  more ? data : data[0] ? [data[0]] : [];
  }, [data, more]);

  return !originData.length ? null : (
    <div className="box txn-box" key={key}>
      <p className="box-title">{title}</p>
        <div className="box-content" >
          <div>
            {originData.map((d: any) => (
              <div className='txn-item' key={d.Timestamp}>
                  <div className="txn-header" >
                    Timestamp: {toUTCTime(d.Timestamp)}
                  </div>
                  <div className="txn-state"> 
                    <div className='box-key'>InvokeContextType:</div>
                    <div className='box-val'>{d.InvokeContextType}</div>
                    {d.Target ? (
                      <>
                        <div className='box-key'>Target:</div>
                        <div className='box-val'>
                          <AddressText addrIndex={d.AddressIndex} addr={d.Target} />
                        </div>
                      </>
                    ) : null}
                    {d.Initiator ? (
                      <>
                        <div className='box-key'>Initiator:</div>
                        <div className='box-val'>
                          <AddressText addrIndex={d.AddressIndex} addr={d.Initiator} />
                        </div>
                      </>
                    ) : null}
                    <div className='box-key'>BuildNum:</div>
                    <div className='box-val'>{d.BuildNum}</div>
                    <div className='box-key'>Function:</div>
                    <div className='box-val blue-font'>
                      <Tooltip placement={'top'} trigger="hover" overlay={
                        <ReactJson
                          src={d.Arguments || {}}
                          style={{ background: "none" }}
                          displayObjectSize={false}
                          enableClipboard={false}
                          displayDataTypes={false}
                          displayArrayKey={false}
                          collapsed={2}
                          name={false}
                          theme="chalk"
                        />}>
                          <>
                            {d.Function}@{d.Contract}
                          </>
                      </Tooltip>
                    </div>
                    <div className='box-key'>Block Height:</div>
                    <div className='box-val'>{d.Height}</div>
                    <div className='box-key'>Shard:</div>
                    <div className='box-val'>{toShard(d.ShardIndex, d.ShardOrder)}</div>
                    <div className='box-key'>Return Value:</div>
                    <div className='box-val'>{d.InvokeResult}</div>
                  </div>
              </div>
            ))}
          </div>
          {data.length > 1 ? (
            <div className='center bottom'>
              <MoreSwitch onChange={(s: boolean) => setMore(s)} value={more} />
            </div>
          ) : null}
      </div>
    </div>
  )
};
export const BlockBox = ({data, key, title, shardOrder = '0'}: BoxItemType) => {
  const [more, setMore] = React.useState<boolean>(false);
  const [originData, setOriginData] = React.useState<any>([]);

  React.useEffect(() => {
    setOriginData(more ? data : data[0] ? [data[0]] : [])
  }, [data, more]);

  
  return !originData.length ? null : (
    <div className="box block-box" key={key}>
      <p className="box-title">{title}</p>
        <div className="box-content" >
          <div>
            {originData.map((d: any, index: number) => (
              <div className='block-item' key={d.Timestamp}>
                  <div className="block-header" >
                    Block Height: #{d.Height}
                  </div>
                  <div className="block-state"> 
                    <div className='box-key'>Shard:</div>
                    <div className='box-val'>{toShard(d.ShardIndex, shardOrder)}</div>
                    <div className='box-key'>Timestamp:</div>
                    <div className='box-val'>{toUTCTime(d.Timestamp)}</div>
                    <div className='box-key'>Miner:</div>
                    <div className='box-val'>
                      <AddressText addr={d.Miner} />
                    </div>
                    <div className='box-key'>TxnCount:</div>
                    <div className='box-val'>{d.TxnCount}</div>
                    <div className='box-key'>Confirm Txn:</div>
                    <div className='box-val'>
                      {d.ConfirmTxn ? (
                        <MoreSwitch onChange={(s: boolean) => {
                          originData[index].showConfirm = !d.showConfirm;
                          setOriginData([...originData]);
                          console.log(originData, index, d.showConfirm)
                        }} value={!!d.showConfirm}/> 
                      ) : 0}
                    </div>
                  </div>
                  {(d.showConfirm && d.ConfirmTxn) ? (
                    <div className='confirm-txn'>
                      {(d.ConfirmTxn || []).map((txn: any) => (
                        <div className='confirm-txn-item' key={txn.Timestamp}>
                          <div className='box-key'>Return Value:</div>
                          <div className='box-val'>{txn.InvokeResult}</div>
                          {/* <div className='box-key'>GasBurnt:</div>
                          <div className='box-val'>{txn.GasBurnt}</div> */}
                          <div className='box-key'>InvokeContextType:</div>
                          <div className='box-val'>{txn.InvokeContextType}</div>
                          {txn.Target ? (
                            <>
                              <div className='box-key'>Target:</div>
                              <div className='box-val'>
                                <AddressText addr={txn.Target} />
                              </div>
                            </>
                          ) : null}
                          {txn.Initiator ? (
                            <>
                              <div className='box-key'>Initiator:</div>
                              <div className='box-val'>
                                <AddressText addr={txn.Initiator} />
                              </div>
                            </>
                          ) : null}
                          <div className='box-key'>OriginateShardOrder:</div>
                          <div className='box-val'>{txn.ShardOrder ** 2}</div>
                          <div className='box-key'>OriginateShardIndex:</div>
                          <div className='box-val'>{txn.ShardIndex}</div>
                          <div className='box-key'>BuildNum:</div>
                          <div className='box-val'>{txn.BuildNum}</div>
                          <div className='box-key'>Timestamp:</div>
                          <div className='box-val'>{toUTCTime(txn.Timestamp)}</div>
                          <div className='box-key'>Function:</div>
                          <div className='box-val blue-font'>
                            <Tooltip placement={'top'} trigger="hover" overlay={
                              <ReactJson
                                src={txn.Arguments || {}}
                                style={{ background: "none" }}
                                displayObjectSize={false}
                                enableClipboard={false}
                                displayDataTypes={false}
                                displayArrayKey={false}
                                collapsed={2}
                                name={false}
                                theme="chalk"
                              />}>
                                <>
                                  {txn.Function}@{txn.Contract}
                                </>
                            </Tooltip>
                          </div>
                        </div>
                      ))}
                    </div>
                    ) : null}
              </div>
            ))}
          </div>
          {data.length > 1 ? (
            <div className='center bottom'>
              <MoreSwitch onChange={(s: boolean) => setMore(s)} value={more} />
            </div>
          ) : null}
      </div>
    </div>
  )
};

export const ProfingBox = ({data, key, title}: BoxItemType) => {

  const maxHeight = React.useMemo(() => {
    return  Math.max(...(data.map((d: ProfingType) => d.BlockHeight)));
  }, [data]);

  const [totalTxn, totalTPS] = React.useMemo(() => {
    let tTxn = 0
    let tTPS = 0
    data.forEach((d: ProfingType) => {
      tTxn = tTxn + Number(d.TxnCount)
      tTPS = tTPS + Number(d.TPS)
    })
    return  [tTxn, tTPS]
  }, [data]);

  return !data.length ? null : (
    <div className="box profing-box" key={key}>
      <p className="box-title">{title}</p>
        <div className="box-content" >
          <div className='profing-header'>
            <div className='profing-header-item'>
              <div className='box-val'>{maxHeight}</div>
              <div className='box-key'>Block Height</div>
            </div>
            <div className='profing-header-item'>
              <div className='box-val'>{toPrettyNumber(totalTxn)}</div>
              <div className='box-key'>Overall Transactions</div>
            </div>
            <div className='profing-header-item'>
              <div className='box-val'>{totalTPS}&nbsp;TPS</div>
              <div className='box-key'>Overall Throughput</div>
            </div>
          </div>
         {(data || []).map((d: ProfingType) => (
            <div className='profing-item' key={d.ShardIndex}>
              <div> shard {d.ShardIndex}, Height {d.BlockHeight} </div>
              <div> {toPrettyNumber(d.TxnCount)} </div>
              <div> {d.TPS}&nbsp;TPS </div>
            </div>
          ))}
      </div>
    </div>
  )
};

