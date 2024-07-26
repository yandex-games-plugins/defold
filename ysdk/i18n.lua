---@type table|nil
local current_translations = nil
local change_lang_callbacks = {}

---@param code string The language code
local function parse_translations(code)
  local data, error = sys.load_resource("/i18n/" .. code .. ".json")
  if error then
    print("No translation file for lang: " .. code)
    return nil
  end
  return json.decode(data)
end

---@param path string The key to translation
---@return string
local function find_translation(path)
  local value = current_translations

  path = path:gsub("[{}% ]", "")
  for key in path:gmatch("[^%.]+") do
    value = value[key]
    if value == nil then break end
  end

  if value == nil then
    return ""
  else
    return value
  end
end

local M = {}

function M.on(cb)
  cb()
  change_lang_callbacks[cb] = true
end

function M.off(cb)
  change_lang_callbacks[cb] = nil
end

function M.get_translations()
  return current_translations
end

---@param code string The language code
function M.set_language(code)
  local translations = parse_translations(code)
  if translations ~= nil then
    current_translations = translations
    for cb, _ in pairs(change_lang_callbacks) do cb() end
  end
end

---@param key string The key to translation
function M.key(key)
  if current_translations == nil then
    current_translations = parse_translations(ysdk.environment.i18n.lang)
    if current_translations == nil then
      current_translations = parse_translations("en")
    end
    if current_translations == nil then
      return ""
    end
  end

  return find_translation(key)
end

function M.gui(node_id, key)
  gui.set_text(gui.get_node(node_id), M.key(key))
end

return M;
